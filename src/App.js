import './App.css';
import { Routes, Route, HashRouter } from 'react-router-dom';
import ViewDataBase from './Pages/ViewDataBase';
import Documents from './Pages/Documents';
import NoPage from './Pages/NoPage';
import Collections from './Pages/Collections';
import EditDocument from './Pages/EditDocument';


function App() {

  return (
    <div className="App">
      <HashRouter>
        <Routes>
          <Route index element={<ViewDataBase />}/>
          <Route index element={<Collections />} />
          <Route index element={<Documents />} />
          <Route path="/viewDataBase" element={<ViewDataBase />} />
          <Route path="/Collections" element={<Collections />} />
          <Route path="/Documents" element={<Documents />} />
          <Route path="/EditDocument" element={<EditDocument />} />
          <Route path="*" element={<NoPage />} />
        </Routes>
      </HashRouter>

    </div>
  );
}

export default App;
